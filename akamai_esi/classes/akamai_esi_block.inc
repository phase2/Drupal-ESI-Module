<?php

class akamai_esi_block extends esi_block {
  public function send_esi() {
    if (function_exists('getallheaders')) {
      $headers = getallheaders();
      // Akamai-Origin-Hop is present behind a "true" Akamai CDN system
      // Surrogate-Capability is an optional header set by the ETS for development
      return (!empty($headers['Akamai-Origin-Hop']) || !empty($headers['Surrogate-Capability']) || parent::send_esi());
    } else {
      return parent::send_esi();
    }
  }

  // TODO: this effectively prevents any caching other than per user and anonymous
  public function replace_block($callback, $block) {
    return '<esi:choose>
            <esi:when test="$(HTTP_COOKIE{$(HTTP_COOKIE{\'ESISESS\'})})">
              <esi:include src="' . $callback . '$(HTTP_COOKIE{$(HTTP_COOKIE{\'ESISESS\'})})" />
            </esi:when>
            <esi:otherwise>
              <esi:include src="' . $callback . '0" />
            </esi:otherwise>
          </esi:choose>';
  }
}
