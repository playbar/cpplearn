/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf -m 10 ./iconv_open-zos.gperf  */
/* Computed positions: -k'4,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 17 "./iconv_open-zos.gperf"
struct mapping { int standard_name; const char vendor_name[10 + 1]; };

#define TOTAL_KEYWORDS 41
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 11
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 51
/* maximum key range = 49, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
mapping_hash (register const char *str, register size_t len)
{
  static const unsigned char asso_values[] =
    {
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 31, 28,
       9,  0, 26, 20,  3,  7,  0,  6, 30, 15,
      14, 11, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52,  0, 52,  0, 52, 52, 52,  0,
      18, 52,  2, 52, 52, 52, 52,  1, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
      52, 52
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[3]+6];
      /*FALLTHROUGH*/
      case 3:
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

struct stringpool_t
  {
    char stringpool_str3[sizeof("GBK")];
    char stringpool_str5[sizeof("ASCII")];
    char stringpool_str6[sizeof("CP1253")];
    char stringpool_str7[sizeof("EUC-TW")];
    char stringpool_str8[sizeof("EUC-KR")];
    char stringpool_str9[sizeof("CP1256")];
    char stringpool_str10[sizeof("ISO-8859-8")];
    char stringpool_str11[sizeof("ISO-8859-13")];
    char stringpool_str12[sizeof("CP1046")];
    char stringpool_str13[sizeof("ISO-8859-6")];
    char stringpool_str14[sizeof("CP922")];
    char stringpool_str15[sizeof("CP1252")];
    char stringpool_str16[sizeof("ISO-8859-9")];
    char stringpool_str17[sizeof("ISO-8859-7")];
    char stringpool_str18[sizeof("CP437")];
    char stringpool_str19[sizeof("ISO-8859-2")];
    char stringpool_str20[sizeof("CP932")];
    char stringpool_str21[sizeof("GB2312")];
    char stringpool_str22[sizeof("CP866")];
    char stringpool_str23[sizeof("CP856")];
    char stringpool_str24[sizeof("EUC-JP")];
    char stringpool_str25[sizeof("CP869")];
    char stringpool_str26[sizeof("CP1255")];
    char stringpool_str28[sizeof("CP862")];
    char stringpool_str29[sizeof("CP852")];
    char stringpool_str30[sizeof("ISO-8859-5")];
    char stringpool_str31[sizeof("ISO-8859-15")];
    char stringpool_str32[sizeof("CP1254")];
    char stringpool_str33[sizeof("CP1125")];
    char stringpool_str34[sizeof("CP1251")];
    char stringpool_str35[sizeof("CP943")];
    char stringpool_str36[sizeof("ISO-8859-4")];
    char stringpool_str37[sizeof("CP1250")];
    char stringpool_str38[sizeof("ISO-8859-1")];
    char stringpool_str39[sizeof("CP1124")];
    char stringpool_str40[sizeof("CP855")];
    char stringpool_str41[sizeof("CP949")];
    char stringpool_str42[sizeof("CP874")];
    char stringpool_str45[sizeof("CP864")];
    char stringpool_str47[sizeof("CP861")];
    char stringpool_str51[sizeof("CP850")];
  };
static const struct stringpool_t stringpool_contents =
  {
    "GBK",
    "ASCII",
    "CP1253",
    "EUC-TW",
    "EUC-KR",
    "CP1256",
    "ISO-8859-8",
    "ISO-8859-13",
    "CP1046",
    "ISO-8859-6",
    "CP922",
    "CP1252",
    "ISO-8859-9",
    "ISO-8859-7",
    "CP437",
    "ISO-8859-2",
    "CP932",
    "GB2312",
    "CP866",
    "CP856",
    "EUC-JP",
    "CP869",
    "CP1255",
    "CP862",
    "CP852",
    "ISO-8859-5",
    "ISO-8859-15",
    "CP1254",
    "CP1125",
    "CP1251",
    "CP943",
    "ISO-8859-4",
    "CP1250",
    "ISO-8859-1",
    "CP1124",
    "CP855",
    "CP949",
    "CP874",
    "CP864",
    "CP861",
    "CP850"
  };
#define stringpool ((const char *) &stringpool_contents)

static const struct mapping mappings[] =
  {
    {-1}, {-1}, {-1},
#line 68 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str3, "IBM-936"},
    {-1},
#line 28 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str5, "00367"},
#line 60 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str6, "IBM-1253"},
#line 67 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str7, "IBM-eucTW"},
#line 66 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str8, "IBM-eucKR"},
#line 63 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str9, "IBM-1256"},
#line 35 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str10, "ISO8859-8"},
#line 37 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str11, "ISO8859-13"},
#line 54 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str12, "IBM-1046"},
#line 33 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str13, "ISO8859-6"},
#line 50 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str14, "IBM-922"},
#line 59 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str15, "IBM-1252"},
#line 36 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str16, "ISO8859-9"},
#line 34 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str17, "ISO8859-7"},
#line 39 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str18, "IBM-437"},
#line 30 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str19, "ISO8859-2"},
#line 51 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str20, "IBM-eucJC"},
#line 64 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str21, "IBM-eucCN"},
#line 47 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str22, "IBM-866"},
#line 43 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str23, "IBM-856"},
#line 65 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str24, "EUCJP"},
#line 48 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str25, "IBM-869"},
#line 62 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str26, "IBM-1255"},
    {-1},
#line 45 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str28, "IBM-862"},
#line 41 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str29, "IBM-852"},
#line 32 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str30, "ISO8859-5"},
#line 38 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str31, "ISO8859-15"},
#line 61 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str32, "IBM-1254"},
#line 56 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str33, "IBM-1125"},
#line 58 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str34, "IBM-1251"},
#line 52 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str35, "IBM-943"},
#line 31 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str36, "ISO8859-4"},
#line 57 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str37, "IBM-1250"},
#line 29 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str38, "ISO8859-1"},
#line 55 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str39, "IBM-1124"},
#line 42 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str40, "IBM-855"},
#line 53 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str41, "IBM-949"},
#line 49 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str42, "TIS-620"},
    {-1}, {-1},
#line 46 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str45, "IBM-864"},
    {-1},
#line 44 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str47, "IBM-861"},
    {-1}, {-1}, {-1},
#line 40 "./iconv_open-zos.gperf"
    {(int)(size_t)&((struct stringpool_t *)0)->stringpool_str51, "IBM-850"}
  };

const struct mapping *
mapping_lookup (register const char *str, register size_t len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = mapping_hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register int o = mappings[key].standard_name;
          if (o >= 0)
            {
              register const char *s = o + stringpool;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &mappings[key];
            }
        }
    }
  return 0;
}
