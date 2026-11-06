# Include inside the twinsun.com HTTPS VirtualHost, before any catch-all proxy.
# Requires mod_ssl, mod_proxy, mod_proxy_http and mod_alias.
RedirectMatch 302 "^/soap-v2$" "/soap-v2/"
Alias "/soap-v2/" "/var/www/soap-note-assistant-v2/"
<Directory "/var/www/soap-note-assistant-v2">
    DirectoryIndex index.html
    Options -Indexes
    AllowOverride None
    Require all granted
</Directory>

SSLProxyEngine On
SSLProxyVerify require
SSLProxyCheckPeerName On
SSLProxyCACertificateFile /etc/pki/tls/certs/ca-bundle.crt
<Location "/soap-api/transcribe">
    LimitRequestBody 33554432
</Location>
ProxyPassMatch "^/soap-api/(health|transcribe)$" "https://llm-jp.com/soap-api/$1" connectiontimeout=15 timeout=1800 retry=0 disablereuse=On
ProxyPassMatch "^/llmjp/(auth/login|generate|batch)$" "https://llm-jp.com/llmjp/$1" connectiontimeout=15 timeout=1800 retry=0 disablereuse=On
