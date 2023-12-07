#ifndef METALANG_MACRO_MAP_HPP
#define METALANG_MACRO_MAP_HPP

#define META_LANG_PRIVATE_MACRO_MAP_1(action, entry, ...) action(entry)
#define META_LANG_PRIVATE_MACRO_MAP_2(action, entry, ...) \
  action(entry);                                          \
  META_LANG_PRIVATE_MACRO_MAP_1(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_3(action, entry, ...) \
  action(entry);                                          \
  META_LANG_PRIVATE_MACRO_MAP_2(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_4(action, entry, ...) \
  action(entry);                                          \
  META_LANG_PRIVATE_MACRO_MAP_3(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_5(action, entry, ...) \
  action(entry);                                          \
  META_LANG_PRIVATE_MACRO_MAP_4(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_6(action, entry, ...) \
  action(entry);                                          \
  META_LANG_PRIVATE_MACRO_MAP_5(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_7(action, entry, ...) \
  action(entry);                                          \
  META_LANG_PRIVATE_MACRO_MAP_6(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_8(action, entry, ...) \
  action(entry);                                          \
  META_LANG_PRIVATE_MACRO_MAP_7(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_9(action, entry, ...) \
  action(entry);                                          \
  META_LANG_PRIVATE_MACRO_MAP_8(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_10(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_9(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_11(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_10(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_12(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_11(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_13(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_12(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_14(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_13(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_15(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_14(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_16(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_15(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_17(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_16(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_18(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_17(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_19(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_18(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_20(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_19(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_21(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_20(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_22(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_21(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_23(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_22(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_24(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_23(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_25(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_24(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_26(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_25(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_27(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_26(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_28(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_27(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_29(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_28(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_30(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_29(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_31(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_30(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_32(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_31(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_33(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_32(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_34(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_33(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_35(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_34(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_36(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_35(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_37(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_36(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_38(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_37(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_39(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_38(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_40(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_39(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_41(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_40(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_42(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_41(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_43(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_42(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_44(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_43(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_45(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_44(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_46(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_45(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_47(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_46(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_48(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_47(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_49(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_48(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_50(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_49(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_51(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_50(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_52(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_51(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_53(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_52(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_54(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_53(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_55(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_54(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_56(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_55(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_57(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_56(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_58(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_57(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_59(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_58(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_60(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_59(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_61(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_60(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_62(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_61(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_63(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_62(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_64(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_63(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_65(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_64(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_66(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_65(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_67(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_66(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_68(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_67(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_69(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_68(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_70(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_69(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_71(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_70(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_72(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_71(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_73(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_72(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_74(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_73(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_75(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_74(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_76(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_75(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_77(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_76(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_78(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_77(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_79(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_78(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_80(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_79(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_81(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_80(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_82(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_81(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_83(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_82(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_84(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_83(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_85(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_84(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_86(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_85(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_87(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_86(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_88(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_87(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_89(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_88(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_90(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_89(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_91(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_90(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_92(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_91(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_93(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_92(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_94(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_93(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_95(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_94(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_96(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_95(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_97(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_96(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_98(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_97(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_99(action, entry, ...) \
  action(entry);                                           \
  META_LANG_PRIVATE_MACRO_MAP_98(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_100(action, entry, ...) \
  action(entry);                                            \
  META_LANG_PRIVATE_MACRO_MAP_99(action, __VA_ARGS__)

#define MACRO_MAP(n, ...) META_LANG_PRIVATE_MACRO_MAP_##n(__VA_ARGS__)

#endif  // METALANG_MACRO_MAP_HPP
