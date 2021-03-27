FROM php:apache

RUN pecl install redis \
	&& docker-php-ext-enable redis

COPY index.php /var/www/html/