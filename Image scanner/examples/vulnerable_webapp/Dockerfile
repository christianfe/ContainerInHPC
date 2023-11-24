FROM php:8.1-apache

ENV APACHE_DOCUMENT_ROOT /var/www/html/public

RUN apt-get update
RUN apt-get install -y iputils-ping ssh netcat-traditional

COPY index.php /var/www/html/index.php

WORKDIR /var/www/html