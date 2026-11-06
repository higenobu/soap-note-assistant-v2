# SOAP新版を新EC2へ配置

新版は `https://twinsun.com/soap-v2/` に配信します。新EC2は画面配信とAPI中継を担当します。音声認識とLLM推論には `llm-jp.com` の既存経路を使います。APIの実行・記録方針は既存環境に従います。

新EC2上のこのディレクトリで実行します。

```sh
sudo install -d -m 755 /var/www/soap-note-assistant-v2
sudo install -m 644 static/index.html static/style.css static/core.js static/report.js static/app.js /var/www/soap-note-assistant-v2/
sudo install -d -m 755 /etc/httpd/llmjp
sudo install -m 644 deploy/apache-soap-v2.inc /etc/httpd/llmjp/apache-soap-v2.inc
```

新EC2の `/etc/httpd/conf.d/twinsun.conf` のHTTPS VirtualHost内で、広い範囲のProxyPassがあればその前に次を追加します。同じAPIの経路を設定済みの場合は、重複しないよう既存設定を確認します。

```apache
Include /etc/httpd/llmjp/apache-soap-v2.inc
```

```sh
sudo httpd -t && sudo systemctl reload httpd
curl -fsS https://twinsun.com/soap-v2/ -o /dev/null
curl -fsS https://twinsun.com/soap-api/health
```

初回は架空の音声で、ログイン、文字起こし、分類、要約を確認します。
話者確認は初期状態でオフです。必要なら話者の役割確認をオンにして候補を推定または手動で入力できます。
内容だけで分類した場合、発言者が分からないと判断できない箇所は「要確認」に残します。
医師が原音と照合してから、コピーまたは印刷・PDF保存します。
