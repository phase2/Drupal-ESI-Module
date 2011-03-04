<?php

class esi_block {
  public function send_esi() {
    return isset($_GET['ESI_FORCE']);
  }

  public function replace_block($callback, &$block) {
    return '<esi:include src="' . $callback . '" />';
  }

  public function get_block($callback, &$block) {
    return theme('block', $block);
  }
}
