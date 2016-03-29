<?php


/**
 * @file
 * Hooks provided by the Juicebox module.
 */


/**
 * Allow modules to alter the Juicebox gallery object used to build gallery
 * embed code and XML before rendering.
 *
 * @param object $juicebox
 *   A Juicebox gallery object that contains the gallery which is going to be
 *   rendered. This object can be further manipulated using any methods from
 *   JuiceboxGalleryDrupalInterface (which includes JuiceboxGalleryInterface).
 * @param mixed $data
 *   The raw Drupal data that was used to build this gallery. Provided for
 *   context.
 */
function hook_juicebox_gallery_alter($juicebox, $data) {
  // See if this is a gallery sourced from a view.
  $id_args = $juicebox->getIdArgs();
  if ($id_args[0] == 'viewsstyle') {
    $view = $data;
    // Assume we have a view called "galleries" and a page called "page_1" that
    // structures galleries based on a taxonomy term contextual filter. We want
    // the juicebox "galleryDescription" option to be the term description, but
    // because this term description is dynamic (based on contextual filter) we
    // can't statically define it in the view's Juicebox settings. This hook
    // let's us do the job dynamically.
    if ($view->name == 'galleries' && $view->current_display == 'page_1') {
      if (!empty($view->args)) {
        $term = taxonomy_term_load($view->args[0]);
        if (!empty($term->description)) {
          // Add the description to the gallery.
          $juicebox->addOption('gallerydescription', strip_tags($term->description));
        }
      }
    }
  }
}


/**
 * Allow modules to alter the classes that are instantiated when a Juicebox
 * object is created.
 *
 * @param array $classes
 *   An associative array containing the class names that will be instantiated:
 *   - gallery: A gallery object dependency (implementing
 *     JuiceboxGalleryInterface) that's used to create the script and markup
 *     outputs of a Juicebox gallery.
 *   - juicebox: A Juicebox gallery wrapper (implementing
 *     JuiceboxGalleryWrapperInterface) that will be used to wrap/decorate the
 *     gallery object with Drupal-specific logic and structures.
 * @param array $library
 *   Juicebox javascript library data as provided through Libraries API.
 *   Provided for context.
 *
 * @see juicebox()
 */
function hook_juicebox_classes_alter(&$classes, $library) {
  // Provide custom (global) overrides to a Juicebox library.
  $classes['juicebox'] = 'MyJuiceboxGalleryWrapper';
  // Swap out the gallery dependency object because some future Juicebox
  // javascript library requires different embed or XML output.
  if (!empty($library['version']) && $library['version'] == 'Pro 12.3') {
    $classes['gallery'] = 'FutureJuiceboxGallery';
  }
}


/**
 * Allow modules to alter the class used for a Juicebox XML loader.
 *
 * Any Drupal formatter that creates Juicebox embed code must also provide a
 * way for the associated Juicebox XML to be generated. This is typically
 * handled via a seperate request that can be routed and managed any way you
 * like (such as a dedicated Drupal menu item). If you want to use the existing
 * "juicebox/xml/%" menu item for this, you can specifiy a custom XML loader
 * class (implementing JuiceboxXmlInterface) and then "register" it with this
 * hook.
 *
 * @param string $xml_loader_class
 *   The Juicebox XML loader class that should be instantiated given the passed
 *   URL args.
 * @param array $args
 *   The args that appear after /juicebox/xml in the path.
 *
 * @see juicebox_page_xml()
 */
function hook_juicebox_xml_class_alter(&$xml_loader_class, $args) {
  if (!empty($args[0]) && $args[0] == 'mywidget') {
    $xml_loader_class = 'JuiceboxXmlMyWidget';
  }
}
