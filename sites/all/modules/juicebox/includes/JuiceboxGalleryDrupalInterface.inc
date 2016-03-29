<?php


/**
 * @file
 * Interface definition for a Juicebox gallery that includes Drupal
 * functionality.
 */


/**
 * Interface definition for a Juicebox gallery that includes Drupal
 * functionality.
 */
interface JuiceboxGalleryDrupalInterface extends JuiceboxGalleryInterface {

  /**
   * Initialize in preparation to represent a specific gallery.
   *
   * @param array $id_args
   *   An indexed array of simple string arguments that describe this gallery.
   *   This is typically based on the arguments that will be used to create a
   *   URL for the gallery XML, but no formal structure is strictly required.
   *   This information should uniquely identify the gallery.
   * @param array $settings
   *   An associative array of settings data for this gallery. This will
   *   typically contain both generic gallery settings (that pertain to this
   *   object) as well as formatter settings (that are only used externally by
   *   a formatter plugin).
   * @param mixed $data
   *   Drupal source data that was used to build the gallery. This is included
   *   purely for reference.
   */
  public function init($id_args, $settings = array(), $data = NULL);

  /**
   * Check if the object has been initialized for use as a specific gallery.
   *
   * @return boolean
   *   Returns boolean TRUE if the object has been initialized, FALSE otherwise.
   */
  public function isInitialized();

  /**
   * Getter method for the id args that describe this gallery.
   *
   * @return array
   *   Returns an indexed array of id args.
   */
  public function getIdArgs();

  /**
   * Getter method for common gallery settings.
   *
   * @return array
   *   Returns an associative array of common gallery settings.
   */
  public function getSettings();

  /**
   * Common post-build tasks that should take place whenever a gallery of any
   * type/source is built.
   */
  public function runCommonBuild();

  /**
   * Utility to extract image source data in an array structure that can be
   * used when adding a new image to the gallery.
   *
   * @param array $image_item
   *   An associative array of file field item data for the main image.
   * @param string $image_style
   *   The Drupal image style to apply to the main image.
   * @param array $thumb_item
   *   An associative array of file field item data for the thumbnail
   *   image.
   * @param string $thumb_style
   *   The Drupal image style to apply to the thumbnail image.
   * @return array
   *   An associative array of image source URLs that's ready to be added
   *   to a Juicebox gallery, including:
   *   - image_url: URL to the full image to display.
   *   - image_url_small: URL to the full image to display in small screen mode.
   *     Only included if $image_style = juicebox_multisize.
   *   - image_url_large: URL to the full image to display in large screen mode.
   *     Only included if $image_style = juicebox_multisize.
   *   - thumb_url: URL to the thumbnail to display for the image.
   *   - link_url: The Juicebox "link URL" value for the image.
   *   - link_target: The browser target value to use when following a link URL.
   *   - juicebox_compatible: Boolean indicating if the raw source file for the
   *     main image is directly compatible with the Juicebox library.
   */
  public function styleImageSrcData($image_item, $image_style, $thumb_item, $thumb_style);

  /**
   * Build a render array of the embed code for a Juicebox gallery after images
   * and options have been added.
   *
   * Note that this is different from JuiceboxGalleryInterface:renderEmbed() in
   * that it handles ALL considerations for embedding. This includes the
   * addition of the appropriate js and css which would otherwise need to be
   * done independent of renderEmbed(). It also uses the Drupal theme system as
   * opposed to just returning direct markup. Within Drupal this method should
   * always be used instead of renderEmbed().
   *
   * @param string $xml_path
   *   The path to the Juicebox XML for this gallery.
   * @param boolean $add_js
   *   Whether-or-not to add the Juicebox library and gallery-specific
   *   javascript.
   * @param array $context
   *   Optional contextual information that may be used in the display:
   *   - conf_path: A Drupal path within the admin interface where the gallery
   *     can be configured. This may be used within administrative contextual
   *     links for the gallery if provided.
   * @param boolean $add_xml
   *   It may be difficult or impossible to rebuild some types of formatters
   *   during a separate XML request, so this option offers a way around that by
   *   embedding the XML for the gallery directly into the HTML output. This
   *   XML can then be fetched from a request to this same page later via a
   *   sub-request. If TRUE xml-source-path and xml-source-id query strings are
   *   also added to the XML URL to help the XML building logic locate this XML
   *   data later. Setting this option may work around certain limitations but
   *   will likely lead to slower XML generation.
   * @return array
   *   Drupal render array for the embed code that describes a gallery.
   */
  public function buildEmbed($xml_path = '', $add_js = TRUE, $context = array(), $add_xml = FALSE);

  /**
   * Get the "base" values of common Drupal settings used to describe a gallery.
   * This is used for the management of default configuration values.
   *
   * @return array
   *   An associative array of base/default configuration values.
   */
  public function confBaseOptions();

  /**
   * Get common elements for Juicebox configuration forms.
   *
   * Several Juicebox gallery types can share common options and structures.
   * These can be merged into the appropriate forms via a call to this method.
   *
   * @param array $form
   *   The Drupal form array that common elements should be added to.
   * @param array $settings
   *   An associative array containing all the current settings for a Juicebox
   *   gallery (used to set default values).
   * @return array
   *   The common form elements merged within a form array.
   */
  public function confBaseForm($form, $settings);

  /**
   * Get the image style preset options that should be available in
   * configuration style picklists.
   *
   * This is in may ways just a wrapper for image_style_options() that allows
   * the addition of specical options that only Juicebox understands (e.g.
   * "multi-size").
   *
   * @param boolean $allow_multisize
   *   Whether-or-not to allow the addition of a PRO "multi-size" option. This
   *   is only included if this option is TRUE and the currently detected
   *   library is compatible with multi-size features.
   * @return array
   *   An associative array of style presets.
   */
  public function confBaseStylePresets($allow_multisize = TRUE);

}
