<?php

class esi_block {
  public function send_esi() {
    return isset($_GET['ESI_FORCE']);
  }

  public function replace_block($callback, &$block) {
    if (($block->cache & BLOCK_CACHE_PER_USER || $block->cache & BLOCK_CACHE_PER_ROLE)) {
      return '<esi:include src="' . $callback . '" />';
    }
    else {
      return theme('block', $block);
    }
  }

  public function get_block($callback, &$block) {
    return theme('block', $block);
  }
}
