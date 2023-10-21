#define SET_BIT(VAR,BIT_NUM) (VAR|=(1<<BIT_NUM))
#define CLR_BIT(VAR,BIT_NUM) (VAR&=(~(1<<BIT_NUM)))
#define TOG_BIT(VAR,BIT_NUM) (VAR^=(1<<BIT_NUM))
#define GET_BIT(VAR,BIT_NUM) ((VAR & ( 1 << BIT_NUM)) >> BIT_NUM)