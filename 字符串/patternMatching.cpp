#include <iostream>
using namespace std;

bool patternMatching(string s, string p) {
    int lenS = s.length(), lenP = p.length();
    bool res = false;

    for (int i = 0; i <= lenS - lenP; i++) {
        bool isMatched = true;
        for (int j = 0; j < lenP; j++) {
            if (s[i + j] != p[j]) {
                isMatched = false;
                break;
            }
        }
        if (isMatched) {
            cout << i << ' ';
            res = true;
        }
    }

    return res;
}

bool KMP(string s, string p) {
    int tar = 0;
    int pos = 0;
    bool isMatched = false;
    int next[p.length()];

    // next[x]: p[0, x]这段字符串, 使得p[0, k)和p(x-k, x]相等，即使得长度为k的前后缀相等的最大k值
    // 计算next数组
    next[0] = 0;                            // next[0]显然是0
    int prefix = 0;
    int cursor = 1;                         // 从next[1]开始算
    while (cursor < p.length()) {
        if (p[prefix] == p[cursor]) {       /** 
                                             * 考虑p[cursor-1]: 保证了长度为prefix的前后缀相等
                                             * 若p[prefix] == p[cursor], 则p[cursor]可以在p[cursor-1]的基础上扩展一位
                                             * prefix = prefix + 1
                                             */
            ++prefix;
            next[cursor++] = prefix;
        } else if (prefix > 0) {            /** 
                                             * p[prefix] ≠ p[cursor], 需要将prefix缩小
                                             * 试图找到满足p[prefix] = p[cursor]的prefix
                                             * 假设当前前缀为A, 后缀为B, A == B
                                             * 寻找prefix时, 需要让prefix尽可能大
                                             * 找原有前后缀的子集使得前缀 = 后缀
                                             * 等价于找串A相等的前后缀
                                             * 因此prefix = p[prefix - 1]即为一个更小的 k 的相等前后缀
                                             */
            prefix = p[prefix - 1];
        } else {                            /**
                                             * 此处prefix = 0, 不存在相等的前后缀
                                             * 因此next[cursor] = 0;
                                             */
            next[cursor++] = 0;
        }
    }

    // kmp 匹配过程
    while (tar < s.length()) {              // 遍历主串
        if (s[tar] == p[pos]) {             // 匹配 
            ++tar;
            ++pos;
        } else if (pos > 0) {               // 失配, 有已经匹配的子串, 查询其next数组看是否可以跳过部分字符
            pos = next[pos - 1];
        } else {                            // 失配, 无已经匹配的子串, 主串向后一个字符
            ++tar;
        }

        if (pos == p.length()) {
            isMatched = true;
            cout <<  tar - pos << ' ';      // 匹配完毕, 输出index
            pos = next[pos - 1];            // 进入下一轮匹配, 看是否有多个匹配项
        }
    }

    return isMatched;
}