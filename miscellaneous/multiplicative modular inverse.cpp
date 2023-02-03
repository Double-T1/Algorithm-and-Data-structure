//multiplicative modular inverse

//ususally base on either little Fermat theorem or Extended Euclidean Algorithn
// i.e a%b == c
//with the former, the modular number(b) has to be a prime number
//with the latter, the modular number(b) and the number to be modular-ed(a) has to be coprime


//succinct as hell, but i don't know why
long long inv(long long a) {
    if (a == 1) return 1;
    // mod-mod/a == remainder
    return (mod-mod/a)*inv(mod%a)%mod;
}