/*
    TRGSW(Torus Ring-GSW) の実装

    myu[X] in Z_N[X]

    1. Scaring
    Bg in Z , Bg > myu[X]
    e_r[X] in T_N[X]  Rounding error

    「Bg dot (a[X],b[X])」dot (myu[X]/Bg     0     ) = (a_r[X],b_r[X]) ~ myu[X] dot (a[X],b[X])
                              (   0       myu[X]/Bg)

    b_r[X] - a_r[X] dot s[X] = myu[X](b[X] - a[X] dot s[X] + e_r[X])
    
    零行列加算
    0を暗号化したTRLWEを行列に加算しマスクする
    myu[X] dot (a[X],b[X]) + 「Bg dot a[X]」dot (a_1[X],b_1[X]) + 「Bg dot b[X]」dot (a_2[X],b_2[X])

    Bgを大きくすると0の暗号文由来のノイズが多いく影響する、しかしBgを小さくすると丸めによるノイズが大きくなる
    そこでDecomposition
    
    2. Decomposition

    3. External Product
*/