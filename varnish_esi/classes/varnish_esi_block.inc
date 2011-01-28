<?php

class varnish_esi_block extends esi_block {

  public function get_block($bid, $page) {
    require_once(dirname(__FILE__)  . '/../../esi.inc');
  
    /**
     * Expect the bid format to be theme:region:module:delta
     * Fail if this doesn't match.
     */
    if (!substr_count($bid, ':') == 3) {
      return FALSE;
    }
    list($theme, $region, $module, $delta) = explode(':', $bid);
  
    // Block content may change per-page.
    // If this is true for the current block, the origin page url should be
    // provided as an argument.
    if ($page) {
      $_GET['q'] = base64_decode($page);
    }
  
    // theme set-up.
    // we need to do this manually, because output is echo'd instead of returned.
    init_theme();
  
    // get the block into a format that can be passed to view-blockk.
    $block = _esi__get_block($theme, $region, $module, $delta);
  
    $output = theme('block', $block);
    /**
     * Pass PER-USER or PER-ROLE cache info to varnish.
     *
     * No-cache is header (TTL) controlled.
     * Per-page is passed as a url argument
     */
    if ($block->cache == BLOCK_NO_CACHE) {
      header("Cache-Control: no-cache, max-age=0");
    }
    elseif ($block->cache & BLOCK_CACHE_PER_USER) {
      // "Cache-control: private" advises proxies that the content is
      // user-specific.  Most proxies will not cache this data - a clever proxy
      // config may make this cacheable.
      header("Cache-Control: private");
      header("X-BLOCK-CACHE: " . BLOCK_CACHE_PER_USER);
    }
    elseif ($block->cache & BLOCK_CACHE_PER_ROLE) {
      header("Cache-Control: private");
      header("X-BLOCK-CACHE: " . BLOCK_CACHE_PER_ROLE);
    }
  
    // For all cacheable blocks, set the TTL based on the block config.
    if ($block->cache != BLOCK_NO_CACHE) {
      $config = _esi__block_settings($module, $delta);
      header("Cache-Control: max-age={$config->ttl}");
    }
  
    return $output;
  }
  
  private function send_esi() {
    return isset($_SERVER['HTTP_X_VARNISH']) || isset($_GET['ESI_FORCE']);
  }
  
  public function replace_block($block) {
    global $theme_key, $base_url;
    if ($this->send_esi()) {
      $bid = "{$theme_key}:{$block->region}:{$block->module}:{$block->delta}";
      $src = $base_url . "/esi/block/{$bid}";
    
      $params = array();
    
      // if the block uses per-page cacheing, add the page param to the URL.
      if ($block->cache & BLOCK_CACHE_PER_PAGE) {
        $src .= '/' . base64_encode($_GET['q']);
      }
    
      // Finally, if the cache-mode is PER-USER or PER-ROLE, advise the proxy.
      // Ideally, the proxy will remove this parameter.
      if ($block->cache & BLOCK_CACHE_PER_USER || $block->cache & BLOCK_CACHE_PER_ROLE) {
        $src .= '/CACHE=' . ($block->cache & BLOCK_CACHE_PER_USER ? 'USER' : 'ROLE');
      }
    
      $output = '<esi:include src="' . $src . '" />';
      return $output;
    }
    else {
      return theme('block', $block);
    }
  }

  /**
   * Add plugin specific options for block configuration form
   */  
  public function config_form(&$form, $config) {
    $options = _esi__ttl_options($config->ttl);
    $form['esi_config']['ttl'] = array(
      '#type' => 'select',
      '#title' => t('TTL'),
      '#description' => t('Time-to-live on the proxy-cache.'),
      '#options' => $options,
      '#default_value' => $config->ttl,
    );
  }
}
