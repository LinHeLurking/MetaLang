#ifndef METALANG_MACRO_MAP_HPP
#define METALANG_MACRO_MAP_HPP

#define META_LANG_PRIVATE_MACRO_MAP_1(action, entry) action(entry)
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

#define META_LANG_PRIVATE_MACRO_MAP_COMMA_1(action, entry) action(entry)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_2(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_1(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_3(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_2(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_4(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_3(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_5(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_4(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_6(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_5(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_7(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_6(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_8(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_7(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_9(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_8(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_10(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_9(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_11(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_10(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_12(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_11(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_13(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_12(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_14(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_13(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_15(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_14(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_16(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_15(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_17(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_16(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_18(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_17(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_19(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_18(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_20(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_19(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_21(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_20(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_22(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_21(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_23(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_22(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_24(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_23(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_25(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_24(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_26(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_25(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_27(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_26(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_28(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_27(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_29(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_28(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_30(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_29(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_31(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_30(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_32(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_31(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_33(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_32(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_34(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_33(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_35(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_34(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_36(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_35(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_37(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_36(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_38(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_37(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_39(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_38(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_40(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_39(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_41(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_40(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_42(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_41(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_43(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_42(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_44(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_43(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_45(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_44(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_46(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_45(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_47(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_46(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_48(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_47(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_49(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_48(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_50(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_49(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_51(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_50(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_52(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_51(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_53(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_52(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_54(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_53(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_55(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_54(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_56(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_55(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_57(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_56(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_58(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_57(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_59(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_58(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_60(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_59(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_61(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_60(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_62(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_61(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_63(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_62(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_64(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_63(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_65(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_64(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_66(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_65(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_67(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_66(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_68(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_67(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_69(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_68(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_70(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_69(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_71(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_70(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_72(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_71(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_73(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_72(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_74(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_73(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_75(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_74(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_76(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_75(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_77(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_76(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_78(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_77(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_79(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_78(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_80(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_79(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_81(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_80(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_82(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_81(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_83(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_82(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_84(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_83(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_85(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_84(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_86(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_85(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_87(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_86(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_88(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_87(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_89(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_88(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_90(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_89(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_91(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_90(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_92(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_91(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_93(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_92(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_94(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_93(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_95(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_94(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_96(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_95(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_97(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_96(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_98(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_97(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_99(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_98(action, __VA_ARGS__)
#define META_LANG_PRIVATE_MACRO_MAP_COMMA_100(action, entry, ...) \
  action(entry), META_LANG_PRIVATE_MACRO_MAP_COMMA_99(action, __VA_ARGS__)

#define META_LANG_PRIVATE_EXTRACT(                                             \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,     \
    _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, \
    _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, \
    _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, \
    _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, \
    _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, \
    _92, _93, _94, _95, _96, _97, _98, _99, _100, v, ...)                      \
  v

#define META_LANG_PRIVATE_MACRO_FOREACH(action, exec, ...)                    \
  EXPAND(EXPAND(META_LANG_PRIVATE_EXTRACT(                                    \
      __VA_ARGS__, exec##_100, exec##_99, exec##_98, exec##_97, exec##_96,    \
      exec##_95, exec##_94, exec##_93, exec##_92, exec##_91, exec##_90,       \
      exec##_89, exec##_88, exec##_87, exec##_86, exec##_85, exec##_84,       \
      exec##_83, exec##_82, exec##_81, exec##_80, exec##_79, exec##_78,       \
      exec##_77, exec##_76, exec##_75, exec##_74, exec##_73, exec##_72,       \
      exec##_71, exec##_70, exec##_69, exec##_68, exec##_67, exec##_66,       \
      exec##_65, exec##_64, exec##_63, exec##_62, exec##_61, exec##_60,       \
      exec##_59, exec##_58, exec##_57, exec##_56, exec##_55, exec##_54,       \
      exec##_53, exec##_52, exec##_51, exec##_50, exec##_49, exec##_48,       \
      exec##_47, exec##_46, exec##_45, exec##_44, exec##_43, exec##_42,       \
      exec##_41, exec##_40, exec##_39, exec##_38, exec##_37, exec##_36,       \
      exec##_35, exec##_34, exec##_33, exec##_32, exec##_31, exec##_30,       \
      exec##_29, exec##_28, exec##_27, exec##_26, exec##_25, exec##_24,       \
      exec##_23, exec##_22, exec##_21, exec##_20, exec##_19, exec##_18,       \
      exec##_17, exec##_16, exec##_15, exec##_14, exec##_13, exec##_12,       \
      exec##_11, exec##_10, exec##_9, exec##_8, exec##_7, exec##_6, exec##_5, \
      exec##_4, exec##_3, exec##_2, exec##_1))(action, __VA_ARGS__))

#define EXPAND(x) x

#define MACRO_FOREACH(action, ...)                                     \
  META_LANG_PRIVATE_MACRO_FOREACH(action, META_LANG_PRIVATE_MACRO_MAP, \
                                  __VA_ARGS__)

#define MACRO_FOREACH_COMMA(action, ...)                                     \
  META_LANG_PRIVATE_MACRO_FOREACH(action, META_LANG_PRIVATE_MACRO_MAP_COMMA, \
                                  __VA_ARGS__)

#define FIRST_(x, ...) x
#define SECOND_(x, y, ...) y
#define FIRST(x) FIRST_ x
#define SECOND(x) SECOND_ x
#define STR(x) #x
#define XSTR(x) STR(x)

#endif  // METALANG_MACRO_MAP_HPP
