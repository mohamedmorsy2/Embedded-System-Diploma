/*
 * name:mohamed morsy
 * file name :common_macros.h
 * description: common macros
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*set a certain bit in any register */
#define SET_BIT(REG,BIT)  (REG |=(1<<BIT))
/*clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT)  (REG &=~(1<<BIT))
/*toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT)  (REG ^=(1<<BIT))
/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) (REG&(1<<BIT))
/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) (! (REG&(1<<BIT)) )

#define GET_BIT(REG,BIT)  ((REG & (1<<BIT))  >> BIT  )





#endif /* COMMON_MACROS_H_ */
