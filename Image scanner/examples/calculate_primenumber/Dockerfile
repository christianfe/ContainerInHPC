FROM openjdk:latest
COPY PrimeNumber.java /var/www/java/PrimeNumber.java
WORKDIR /var/www/java
RUN javac PrimeNumber.java
ENTRYPOINT ["java", "PrimeNumber > /output"]
