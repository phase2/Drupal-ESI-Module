<?php

/**
 * @file
 * implementation of the esi api
 */

/**
 * This used to be theme_esi_tag
 */
function varnish_esi_esi_block($block) {
  global $theme_key, $base_url;

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
