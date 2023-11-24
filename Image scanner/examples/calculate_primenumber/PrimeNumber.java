import java.util.Date;

public class PrimeNumber {
        public static void main(String[] args) {
                Date d1= new Date();
                int maxLimit=1000000;
                System.out.println("Printing prime number from 1 to "+maxLimit);

                for(int number = 2; number<=maxLimit; number++){
                        //Print prime numbers only
                        if(isPrime(number)){
                                System.out.println(number);
                        }
                }
                Date d2=new Date();
                System.out.println("Total time to run the application: "+(d2.getTime()-d1.getTime())/1000);
        }
        /*
         * Prime number is not divisible by any number other than 1 and itself
         * @return true if number is prime
         */
        public static boolean isPrime(int number){
                for(int i=2; i<number; i++){
                        if(number%i == 0){
                                return false; //number is divisible so its not prime
                        }
                }
                return true; //number is prime now
        }
}
