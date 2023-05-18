# Friends of the Princeton University Library

## Local development with Lando

1. `git clone git@github.com:pulibrary/friends_of_pul.git`
2. `cp sites/default/default.settings.php sites/default/settings.php`
3. In `sites/default/settings.php` includd the following lando-style db config values:
    ```
    $databases = array (
      'default' =>
      array (
        'default' =>
        array (
          'database' => 'drupal7',
          'username' => 'drupal7',
          'password' => 'drupal7',
          'host' => 'database',
          'port' => '3306',
          'driver' => 'mysql',
          'prefix' => '',
        ),
      ),
    );
    # needed for CAS logins to work
    $base_url = "http://friends.lndo.site";
    ```
3. Add the following useful local development configuration to the end of `sites/default/settings.php`
    ```
    /* Overrides for the local environment */
    $conf['securepages_enable'] = 0;
    /* This should be set in your php.ini file */
    ini_set('memory_limit', '1G');
    /* Turn off all caching */
    $conf['css_gzip_compression'] = FALSE;
    $conf['js_gzip_compression'] = FALSE;
    $conf['cache'] = 0;
    $conf['block_cache'] = 0;
    $conf['preprocess_css'] = 0;
    $conf['preprocess_js'] = 0;
    /* end cache settings */
    /* Turn on theme debugging. Injects the path to every Template utilized in the HTML source. */
    $conf['theme_debug'] = TRUE;

    /* Makes sure jquery is loaded on every page */
    /* set to false in production */
    $conf['javascript_always_use_jquery'] = TRUE;
    ```
3. `mkdir .ssh` # excluded from version control
4. `cp $HOME/.ssh/id_rsa .ssh/.`
5. `cp $HOME/.ssh/id_rsa.pub .ssh/.` // key should be registered in princeton_ansible deploy role
3. `lando start` Start up lando
4. `cp drush/friends-example.aliases.drushrc.php drush/friends.aliases.drushrc.php`
5. Adjust the config values in the  `drush/friends.aliases.drushrc.php` file to match the current remote drupal environment
    ```
    $aliases['prod'] = array (
        'uri' => 'https://fpul.princeton.edu',
        'root' => '', // Add root
        'remote-user' => 'deploy', // Add user
        'remote-host' => 'app-server-name', // Add app server host name
        'ssh-options' => '-o PasswordAuthentication=no -i .ssh/id_rsa',
        'path-aliases' => array(
            '%dump-dir' => '/tmp',
        ),
        'source-command-specific' => array (
            'sql-sync' => array (
            'no-cache' => TRUE,
            'structure-tables-key' => 'common',
            ),
        ),
        'command-specific' => array (
            'sql-sync' => array (
            'sanitize' => TRUE,
            'no-ordered-dump' => TRUE,
            'structure-tables' => array(
                // You can add more tables which contain data to be ignored by the database dump
                'common' => array('cache', 'cache_*', 'history', 'sessions', 'watchdog', 'cas_data_login', 'captcha_sessions'),
            ),
            ),
        ),
    );
    ```
6. Uncomment the alias block for the local lando site
    ```
    $aliases['local'] = array(
        'root' => '/app', // Path to project on local machine
        'uri'  => 'http://friends.lndo.site',
        'path-aliases' => array(
            '%dump-dir' => '/tmp',
            '%files' => 'sites/default/files',
        ),
    );
    ```
7. `bundle exec cap production database_dump; // this will produce a datestamped dump file in the format "backup-YYYY-MM-DD-{environment}.sql.gz".
1. `lando db-import backup-YYYY-MM-DD-{environment}.sql.gz`
9. `lando drush rsync @friends.prod:%files @friends.local:%files`
10. `lando drush uli your-username`

### Use NPM and Gulp to build styles for drupal theme layer

1. `cd sites/all/themes/pul_base`
2. `lando npm install`
3. `lando gulp deploy` (or any other gulp task)
1. `cd ../friends`
2. `lando npm install`
3. `lando gulp deploy` (or any other gulp task)

## Deploy to server

1. We have capistrano set up to deploy our servers

    1. `cap staging deploy` will deploy the main branch to staging
    1. `BRANCH=other cap staging deploy` will deploy the other branch to staging
