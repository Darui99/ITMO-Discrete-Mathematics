import java.math.BigInteger;
import java.util.*;
import java.util.function.IntFunction;

public class Main {

    public static BigInteger[] mul_r(final BigInteger[] a, final BigInteger[] b) {
        int n = a.length, m = b.length;
        BigInteger[] mul = new BigInteger[n + m];
        for (int i = 0; i < n + m; i++) {
            mul[i] = BigInteger.ZERO;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                mul[i + j] = mul[i + j].add(a[i].multiply(b[j]));
            }
        }
        int sz = n + m;
        while (sz > 1 && mul[sz - 1].compareTo(BigInteger.ZERO) == 0) {
            sz--;
        }
        BigInteger[] res = new BigInteger[sz];
        if (sz >= 0) System.arraycopy(mul, 0, res, 0, sz);
        return res;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        BigInteger r = BigInteger.valueOf(in.nextLong());
        int k = in.nextInt();

        BigInteger[] arr = new BigInteger[k + 1];
        for (int i = 0; i <= k; i++)
            arr[i] = BigInteger.valueOf(in.nextLong());

        IntFunction<BigInteger> calc = nn -> {
            BigInteger n = BigInteger.valueOf(nn);
            BigInteger res = BigInteger.ZERO;
            for (int i = 0; i < arr.length; i++) {
                res = res.add(arr[i].multiply(n.pow(i)));
            }
            return res.multiply(r.pow(nn));
        };

        BigInteger[] f = new BigInteger[2];
        f[0] = BigInteger.ONE;
        f[1] = r.negate();

        BigInteger[] q = new BigInteger[2];
        System.arraycopy(f, 0, q, 0, 2);

        for (int i = 1; i < k + 1; i++) {
            q = mul_r(q, f);
        }

        BigInteger[] st = new BigInteger[q.length - 1];
        for (int i = 0; i < st.length; i++) {
            st[i] = calc.apply(i);
        }

        BigInteger[] p = new BigInteger[st.length];
        for (int i = 0; i < st.length; i++) {
            BigInteger cur = BigInteger.ZERO;
            for (int j = 0; j < i; j++) {
                cur = cur.add(st[i - j - 1].multiply(q[j + 1].negate()));
            }
            p[i] = st[i].subtract(cur);
        }

        int sz = p.length;
        while (sz > 1 && p[sz - 1].compareTo(BigInteger.ZERO) == 0) {
            sz--;
        }
        BigInteger[] resp = new BigInteger[sz];
        System.arraycopy(p, 0, resp, 0, sz);

        sz = q.length;
        while (sz > 1 && q[sz - 1].compareTo(BigInteger.ZERO) == 0) {
            sz--;
        }
        BigInteger[] resq = new BigInteger[sz];
        System.arraycopy(q, 0, resq, 0, sz);

        System.out.println(resp.length - 1);
        for (int i = 0; i < resp.length; i++) {
            System.out.print(resp[i] + " ");
        }
        System.out.println();
        System.out.println(resq.length - 1);
        for (int i = 0; i < resq.length; i++) {
            System.out.print(resq[i] + " ");
        }
    }
}
