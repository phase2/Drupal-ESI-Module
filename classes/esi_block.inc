<?php

class esi_block {
  public function config_form(&$fieldset, $config) {
  }

  public function send_esi() {
    return isset($_SERVER['ESI_FORCE']);
  }

  public function replace_block($callback, &$block) {
    return '<esi:include src="' . $callback . '" />';
  }

  public function get_block($callback, &$block) {
    if ($block->cache == BLOCK_NO_CACHE) {
      header("Cache-Control: no-cache, max-age=0");
    }
    elseif ($block->cache & BLOCK_CACHE_PER_USER) {
      // "Cache-control: private" advises proxies that the content is
      // user-specific.  Most proxies will not cache this data - a clever proxy
      // config may make this cacheable.
      header("Cache-Control: private");
    }
    elseif ($block->cache & BLOCK_CACHE_PER_ROLE) {
      header("Cache-Control: private");
    }

    // For all cacheable blocks, set the TTL based on the block config.
    if ($block->cache != BLOCK_NO_CACHE) {
      $config = _esi__block_settings($module, $delta);
      header("Cache-Control: max-age={$config->ttl}");
    }
    return theme('block', $block);
  }
}
