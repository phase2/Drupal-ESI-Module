<?php

/**
 * @file - definition for esi_block class
 */
class esi_block {
  /**
   * replace_block is called to get the ESI call that should be substituted
   * instead of the contents of the block
   */
  public function replace_block($block) {
    return theme('block', $block);
  }
  
  /**
   * get_block is called to get the contents of the block in response to an
   * ESI path request
   */
  public function get_block($bid, $page) {
    // since the default module does not do any replacement, this is
    // here solely for documentation purposes
    return 'block contents';
  }

  /**
   * configure_block is called to get additional data for the block
   * configuration form
   */
  public function config_form(&$form, $config) {
  }
}
