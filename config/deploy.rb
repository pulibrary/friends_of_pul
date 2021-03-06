# config valid for current version and patch releases of Capistrano
lock "~> 3.15.0"

set :application, "friends_of_pul"
set :repo_url, "git@github.com:pulibrary/friends_of_pul.git"

set :branch, ENV["BRANCH"] || "main"

# Default branch is :master
# ask :branch, `git rev-parse --abbrev-ref HEAD`.chomp

# Default deploy_to directory is /var/www/my_app_name
# set :deploy_to, "/var/www/my_app_name"

# Default value for :format is :airbrussh.
# set :format, :airbrussh

# You can configure the Airbrussh format using :format_options.
# These are the defaults.
# set :format_options, command_output: true, log_file: "log/capistrano.log", color: :auto, truncate: :auto

# Default value for :pty is false
# set :pty, true

# Default value for :linked_files is []
# append :linked_files, "config/database.yml"

# Default value for linked_dirs is []
append :linked_dirs, "log", "tmp"

# Default value for default_env is {}
# set :default_env, { path: "/opt/ruby/bin:$PATH" }

# Default value for local_user is ENV['USER']
# set :local_user, -> { `git config user.name`.chomp }

# Default value for keep_releases is 5
# set :keep_releases, 5

# Uncomment the following to require manually verifying the host key before first deploy.
# set :ssh_options, verify_host_key: :secure


namespace :drupal do
  desc "Include creation of additional Drupal specific shared folders"
  task :prepare_shared_paths do
      on release_roles :app do
          execute :mkdir, '-p', "#{shared_path}/tmp"
          execute :mkdir, '-p', "#{shared_path}/node_modules"
      end
  end

  desc "link files"
  task :link_files do
    on roles(:app) do |host|
      execute "cd #{release_path}/sites/default && ln -sf /home/deploy/settings.php settings.php"
      execute "cd #{release_path}/sites/default && ln -sf #{shared_path}/files files"
      info "linked files"
    end
  end

  desc "Install Assets"
  task :install_assets do
    on roles(:app) do |host|
      execute "cd #{release_path}/sites/all/themes/friends && npm install"
      execute "cd #{release_path}/sites/all/themes/friends && gulp deploy"
      execute "cd #{release_path}/sites/all/themes/pul_base && npm install"
      execute "cd #{release_path}/sites/all/themes/pul_base && gulp deploy"
      info "Installed Assets"
    end
  end

  desc "Clear the drupal cache"
  task :cache_clear do
      on release_roles :drupal_primary do
          execute "sudo -u www-data /usr/local/bin/drush -r #{release_path} cc all"
          info "cleared the drupal cache"
        end
  end

  desc "Update file permissions to follow best security practice: https://drupal.org/node/244924"
  task :set_permissions_for_runtime do
      on release_roles :app do
          execute :find, "#{release_path}", '-type f -exec', :chmod, "640 {} ';'"
          execute :find, "#{release_path}", '-type d -exec', :chmod, "2750 {} ';'"
          execute :find, "#{shared_path}/tmp", '-type d -exec', :chmod, "2770 {} ';'"
      end
  end

  desc "Set the site offline"
  task :site_offline do
      on release_roles :app do
          execute "cd #{release_path}; drush vset --exact maintenance_mode 1; true"
          info "set site to offline"
      end
  end

  desc "Set the site online"
  task :site_online do
      on release_roles :app do
          execute "cd #{release_path}; drush  vdel -y --exact maintenance_mode"
          info "set site to online"
      end
  end

  desc "Update file permissions to follow best security practice: https://drupal.org/node/244924"
  task :set_permissions_for_runtime do
      on release_roles :app do
          execute :find, "#{release_path}", '-type f -exec', :chmod, "640 {} ';'"
          execute :find, "#{release_path}", '-type d -exec', :chmod, "2750 {} ';'"
          execute :find, "#{shared_path}/tmp", '-type d -exec', :chmod, "2770 {} ';'"
      end
  end

  desc "change the owner of the directory to www-data for apache"
  task :update_directory_owner do
      on release_roles :app do
        execute :sudo, "/bin/chown -R www-data #{release_path}"
        execute "sudo /bin/chown -R www-data /var/www/friends_of_pul/current/; true"
      end
  end

  desc "change the owner of the old directories to deploy"
  task :update_directory_owner_deploy do
      on release_roles :app do
        current_release_path = capture 'readlink /var/www/friends_of_pul/current'
        current_release = current_release_path.split('/').last
        release_paths = capture 'ls /var/www/friends_of_pul/releases/'
        release_paths.split(release_paths[14]).each do |release|
          next if release == current_release
          execute :sudo, "/bin/chown -R deploy /var/www/friends_of_pul/releases/#{release}"
          execute :chmod, "-R u+w /var/www/friends_of_pul/releases/#{release}"
        end
        #execute :sudo, "/bin/chown -R deploy /var/www/friends_of_pul/releases/*"
        #execute :chmod, "-R u+w /var/www/friends_of_pul/releases/*"
      end
  end

  namespace :database do

    desc "Run Drush SQL Client against a local sql file SQL_DIR/SQL_GZ"
    task :import_dump do
      invoke "drupal:site_offline"
      invoke "drupal:database:upload_and_import"
      invoke "drupal:site_online"
    end

    desc "Upload the dump file and import it"
    task :upload_and_import do
      gz_sql_name = ENV["SQL_GZ"]
      sql_file_name = gz_sql_name.sub('.gz','')
      on release_roles :drupal_primary do
        upload! ENV["SQL_DIR"] + gz_sql_name, '/tmp/'+gz_sql_name
        execute "gzip -f -d /tmp/#{gz_sql_name}"
        execute "/home/deploy/sql/set_permission.sh"
        execute "drush -r #{release_path} sql-cli < /tmp/"+sql_file_name
      end
    end

    desc "Update the drupal database"
    task :update do
        on release_roles :drupal_primary do
          execute "sudo -u www-data /usr/local/bin/drush -r #{release_path} -y updatedb"
        end
    end
  end
end

namespace :deploy do
  desc "Set file system variables"
  task :after_deploy_check do
      invoke "drupal:prepare_shared_paths"
  end


  desc "Set file system variables"
  task :after_deploy_updated do
      invoke "drupal:link_files"
      invoke "drupal:install_assets"
      invoke "drupal:set_permissions_for_runtime"
      # invoke "drupal:set_file_system_variables"
      invoke "drupal:update_directory_owner"
      # invoke "drupal:enable_smtp"
  end

  after :updated, "deploy:after_deploy_updated"
  before :finishing, "drupal:update_directory_owner_deploy"
end
