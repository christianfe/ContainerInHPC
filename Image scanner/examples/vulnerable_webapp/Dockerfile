FROM php:php:7.0-apache

ENV APACHE_DOCUMENT_ROOT /var/www/html/public

RUN apt-get update
RUN apt-get install -y iputils-ping

COPY index.php /var/www/html/index.php

#WORKDIR /var/www/html