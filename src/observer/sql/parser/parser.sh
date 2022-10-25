###
 # @Author: 181830014 181830014@smail.nju.edu.cn
 # @Date: 2022-10-25 21:00:00
 # @LastEditors: 181830014 181830014@smail.nju.edu.cn
 # @LastEditTime: 2022-10-25 21:02:53
 # @FilePath: /source/ocean/parser.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 
bison -vdty yacc_sql.y
flex lex_sql.l
mv y.tab.c yacc_sql.tab.c
mv y.tab.h yacc_sql.tab.h