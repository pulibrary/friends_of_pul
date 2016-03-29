<?php


/**
 * @file
 * Interface definition for a Juicebox XML loader.
 */


/**
 * Interface definition for a Juicebox XML loader.
 */
interface JuiceboxXmlInterface {

  /**
   * Check access to the Drupal data that will be used to build the gallery.
   *
   * @return boolean
   *   Returns TRUE if access is allowed for the current user and FALSE if not.
   *   Can also return NULL if access cannot be determined.
   */
  public function access();

  /**
   * Get the XML based on loaded data.
   *
   * @return string
   *   Returns XML data describing a Juicebox gallery.
   */
  public function getXml();

}
