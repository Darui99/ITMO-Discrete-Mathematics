import java.math.BigInteger;
import java.util.*;

public class Main {

    public static class BigRealNumber {
        public BigInteger num;
        public BigInteger dem;

        public BigRealNumber(BigInteger num, BigInteger dem) {
            this.num = num;
            this.dem = dem;
        }

        private BigInteger gcd(BigInteger a, BigInteger b) {
            while (a.compareTo(BigInteger.ZERO) > 0 && b.compareTo(BigInteger.ZERO) > 0) {
                if (a.compareTo(b) > 0) {
                    a = a.mod(b);
                } else {
                    b = b.mod(a);
                }
            }
            return a.add(b);
        }

        private BigInteger lcm(BigInteger a, BigInteger b) {
            return a.divide(gcd(a, b)).multiply(b);
        }

        public void normalize() {
            BigInteger g = gcd(num.abs(), dem);
            num = num.divide(g);
            dem = dem.divide(g);
        }


        public BigRealNumber add(BigRealNumber b) {
            BigRealNumber res = new BigRealNumber(num, dem);
            BigInteger l = lcm(res.dem.abs(), b.dem);
            res.num = res.num.multiply(l.divide(res.dem)).add(b.num.multiply(l.divide(b.dem)));
            res.dem = l;
            res.normalize();
            return res;
        }

        public BigRealNumber multiply(BigRealNumber b) {
            BigRealNumber res = new BigRealNumber(num.multiply(b.num), dem.multiply(b.dem));
            res.normalize();
            return res;
        }

        public void print() {
            System.out.print(num + "/" + dem + " ");
        }
    }

    public static BigRealNumber[] mul_r(final BigRealNumber[] a, final BigRealNumber[] b) {
        int n = a.length, m = b.length;
        BigRealNumber[] mul = new BigRealNumber[n + m];
        for (int i = 0; i < n + m; i++) {
            mul[i] = new BigRealNumber(BigInteger.ZERO, BigInteger.ONE);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mul[i + j] = mul[i + j].add(a[i].multiply(b[j]));
            }
        }
        int sz = n + m;
        while (sz > 1 && mul[sz - 1].num.compareTo(BigInteger.ZERO) == 0) {
            sz--;
        }
        BigRealNumber[] res = new BigRealNumber[sz];
        if (sz >= 0) System.arraycopy(mul, 0, res, 0, sz);
        return res;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        long r = in.nextLong();
        int k = in.nextInt();
        long x;

        BigRealNumber arr[] = new BigRealNumber[k + 1];
        for (int i = 0; i <= k; i++) {
            x = in.nextLong();
            arr[i] = new BigRealNumber(BigInteger.valueOf(x), BigInteger.ONE);
        }

        BigRealNumber f[][] = new BigRealNumber[k + 1][];
        for (int t = 0; t <= k; t++) {
            f[t] = new BigRealNumber[1];
            f[t][0] = new BigRealNumber(BigInteger.ONE, BigInteger.ONE);
            for (int i = 1; i <= k; i++) {
                BigRealNumber tmp[] = new BigRealNumber[2];
                tmp[0] = new BigRealNumber(BigInteger.valueOf(i - t), BigInteger.ONE);
                tmp[1] = new BigRealNumber(BigInteger.ONE, BigInteger.ONE);
                f[t] = mul_r(f[t], tmp);
            }
            for (int i = 1; i <= k; i++) {
                for (int j = 0; j < f.length; j++) {
                    f[t][j] = f[t][j].multiply(new BigRealNumber(BigInteger.ONE, BigInteger.valueOf(i)));
                }
            }
        }
        
        BigRealNumber res[] = new BigRealNumber[f.length];
        for (int i = 0; i < f.length; i++) {
            res[i] = new BigRealNumber(BigInteger.ZERO, BigInteger.ONE);
        }
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < f[i].length; j++) {
                res[j] = res[j].add(f[i][j].multiply(arr[i])
                        .multiply(new BigRealNumber(BigInteger.ONE, BigInteger.valueOf(r).pow(i))));
            }
        }

        for (int i = 0; i <= k; i++) {
            res[i].print();
        }
    }
}
