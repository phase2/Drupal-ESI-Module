<?php

class varnish_esi_block extends esi_block {
  public function send_esi() {
    return isset($_SERVER['HTTP_X_VARNISH']) || parent::send_esi();
  }

  public function get_block($callback, &$block) {
    /**
     * Pass PER-USER or PER-ROLE cache info to varnish.
     */
    $output = parent::get_block($callback, $block);
    if ($block->cache & BLOCK_CACHE_PER_USER) {
      header("X-BLOCK-CACHE: " . BLOCK_CACHE_PER_USER);
    }
    elseif ($block->cache & BLOCK_CACHE_PER_ROLE) {
      header("X-BLOCK-CACHE: " . BLOCK_CACHE_PER_ROLE);
    }
    return $output;
  }
}
