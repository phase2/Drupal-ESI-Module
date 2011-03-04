<?php

class varnish_esi_theme extends esi_theme {
  public function send_esi() {
    return isset($_SERVER['HTTP_X_VARNISH']) || parent::send_esi();
  }

  /**
   * called during preprocessing so that plugin can make any alterations
   * needed an alternate template containing the esi include call
   */
  public function preprocess(&$vars, $settings) {
    if ($settings['cache'] & BLOCK_CACHE_PER_USER || $settings['cache'] & BLOCK_CACHE_PER_ROLE) {
      $vars['esi_source'] .= '/CACHE=' . (($settings['cache'] & BLOCK_CACHE_PER_USER) ? 'USER' : 'ROLE');
    }
    $vars['template_files'][] = 'esi';
  }

  public function theme(&$theme_vars, $settings) {
    if ($settings['cache'] & BLOCK_CACHE_PER_USER) {
      header("X-BLOCK-CACHE: " . BLOCK_CACHE_PER_USER);
    }
    elseif ($settings['cache'] & BLOCK_CACHE_PER_ROLE) {
      header("X-BLOCK-CACHE: " . BLOCK_CACHE_PER_ROLE);
    }
    return parent::theme($theme_vars, $settings);
  }
}
