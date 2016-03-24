<?php

/**
 * @file
 * Default theme implementation to display a Browsersync snippet.
 *
 * Available variables:
 * - $host: The host or IP address the Browsersync socket is running on.
 * - $port: The port the Browsersync socket is running on.
 */
?>
<script type='text/javascript' id="__bs_script__">//<![CDATA[
  document.write("<script async src='//<?php print $host; ?>:<?php print $port; ?>/browser-sync/browser-sync-client.js'><\/script>".replace("HOST", location.hostname));
//]]></script>
