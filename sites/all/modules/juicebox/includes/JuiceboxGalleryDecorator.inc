<?php


/**
 * @file
 * Base decorator class for a Juicebox Gallery.
 *
 * We use a decorator pattern here (as opposed to just extending
 * JuiceboxGalleryInterface) so that multiple versions of
 * JuiceboxGalleryInterface classes can be supported simultaneously and
 * swapped-out dynamically. This may be needed to support different embed and
 * XML structures that may be required by different versions of the Juicebox
 * library.
 */


/**
 * Base decorator class for a Juicebox Gallery.
 */
abstract class JuiceboxGalleryDecorator implements JuiceboxGalleryInterface {

  // Base object to be decorated.
  protected $gallery;

  /**
   * Constructor.
   *
   * @param JuiceboxGalleryInterface $juicebox
   *   A plain-PHP Juicebox gallery object.
   */
  public function __construct(JuiceboxGalleryInterface $gallery) {
    $this->gallery = $gallery;
  }

  /**
   * {@inheritdoc}
   */
  public function setId($value, $reset = TRUE) {
    return $this->gallery->setId($value, $reset);
  }

  /**
   * {@inheritdoc}
   */
  public function getId() {
    return $this->gallery->getId();
  }

  /**
   * {@inheritdoc}
   */
  public function addImage($src_data = array(), $title = '', $caption = '', $filter = NULL, $override_id = NULL, $offset = NULL) {
    return $this->gallery->addImage($src_data, $title, $caption, $filter, $override_id, $offset);
  }

  /**
   * {@inheritdoc}
   */
  public function updateImage($image_id, $src_data = array(), $title = '', $caption = '', $filter = TRUE) {
    return $this->gallery->updateImage($image_id, $src_data, $title, $caption, $filter);
  }

  /**
   * {@inheritdoc}
   */
  public function getImages($filtered = FALSE) {
    return $this->gallery->getImages($filtered);
  }

  /**
   * {@inheritdoc}
   */
  public function removeImage($id) {
    return $this->gallery->removeImage($id);
  }

  /**
   * {@inheritdoc}
   */
  public function addOption($option_name, $option_value, $override = TRUE) {
    return $this->gallery->addOption($option_name, $option_value, $override);
  }

  /**
   * {@inheritdoc}
   */
  public function getOptions($filtered = FALSE) {
    return $this->gallery->getOptions($filtered);
  }

  /**
   * {@inheritdoc}
   */
  public function removeOption($option_name) {
    return $this->gallery->removeOption($option_name);
  }

  /**
   * {@inheritdoc}
   */
  public function getChecksum() {
    return $this->gallery->getChecksum();
  }

  /**
   * {@inheritdoc}
   */
  public function renderXml($script_wrap_id = NULL) {
    return $this->gallery->renderXml($script_wrap_id);
  }

  /**
   * {@inheritdoc}
   */
  public function renderEmbed() {
    return $this->gallery->renderEmbed();
  }

  /**
   * {@inheritdoc}
   */
  public function renderJavascript($xml_url, $add_script_tags = FALSE, $jquery_defer = FALSE) {
    return $this->gallery->renderJavascript($xml_url, $add_script_tags, $jquery_defer);
  }

  /**
   * {@inheritdoc}
   */
  public function getJavascriptVars($xml_url) {
    return $this->gallery->getJavascriptVars($xml_url);
  }

}
