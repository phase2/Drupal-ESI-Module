<?php

$plugin = array(
  'block_handler' => array(
    'class' => 'varnish_theme',
    'parent' => 'varnish_esi_block',
    'file' => 'varnish_theme.inc',
    'path' => drupal_get_path('module', 'varnish_esi') .'/classes',
  ),
);

class varnish_theme extends varnish_esi_block {

public function get_theme($block) {
  return "get theme\n";
}

public function replace_theme($block) {
  return "replaced theme\n";
}

}
