<?php

class esi_theme {
  public function send_esi() {
    return isset($_GET['ESI_FORCE']);
  }

  /**
   * this function should add any paths where templates it will suggest
   * in the preprocess method will be found, it is called to populate
   * the theme paths during the alteration of the template registry
   */
  public function theme_paths(&$theme_paths) {
    $theme_paths[] = drupal_get_path('module', 'esi') . '/theme';
  }

  /**
   * called during preprocessing so that plugin can make any alterations
   * needed an alternate template containing the esi include call
   */
  public function preprocess(&$vars, $settings) {
    // base class doesn't handle includes for which include call likely needs to vary per user
    if (!($settings['cache'] & BLOCK_CACHE_PER_USER || $settings['cache'] & BLOCK_CACHE_PER_ROLE)) {
      $vars['template_files'][] = 'esi';
    }
  }

  public function theme(&$theme_vars, $settings) {
    if ($settings['cache'] & BLOCK_CACHE_NO_CACHE) {
      drupal_set_header('Cache-control: no-cache');
    }
    return call_user_func_array('theme', $theme_vars);
  }
}
