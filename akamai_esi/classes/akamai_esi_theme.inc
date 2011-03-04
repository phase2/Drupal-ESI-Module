<?php

class akamai_esi_theme extends esi_theme {
  public function send_esi() {
    return _akamai_esi_send_esi() || parent::send_esi();
  }

  /**
   * called during preprocessing so that plugin can make any alterations
   * needed an alternate template containing the esi include call
   */
  public function preprocess(&$vars, $settings) {
    // base class doesn't handle includes for which include call likely needs to vary per user
    if ($settings['cache'] & BLOCK_CACHE_PER_USER) {
      $vars['esi_source'] .=  '/' . '$(HTTP_COOKIE{$(HTTP_COOKIE{\'' . session_name() . '\'})})';
    }
    else if ($settings['cache'] & BLOCK_CACHE_PER_ROLE) {
      $vars['esi_source'] .= '/' . '$(HTTP_COOKIE{$(HTTP_COOKIE{\'R' . session_name() . '\'})})';
    }
    $vars['template_files'][] = 'esi';
  }

  public function theme(&$theme_vars, $settings) {
    if ($settings['cache'] & BLOCK_CACHE_NO_CACHE) {
      drupal_set_header('Cache-control: no-cache');
    }
    return parent::theme($theme_vars, $settings);
  }
}
