FROM php:8-apache
SHELL ["/bin/bash", "-c"]

ENV APACHE_DOCUMENT_ROOT /var/www/html/public

RUN apt update
RUN apt install -y iputils-ping

COPY index.php /var/www/html/index.php

#WORKDIR /var/www/html
