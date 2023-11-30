FROM openjdk:20-jdk-slim
COPY PrimeNumber.java /var/www/java/PrimeNumber.java
WORKDIR /var/www/java
RUN javac PrimeNumber.java
ENTRYPOINT ["java", "PrimeNumber"]
