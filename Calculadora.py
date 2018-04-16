x = int(input("Digite um numero inteiro: "))
y = int(input("Digite outro numero inteiro: "))


z = input("Digite uma operação")

if z == '+':
   resultado = x + y
   print("o resultado da operação é: ", resultado)

elif z == '-':
   resultado1 = x - y
   print("o resultado da operação é: ", resultado1)		

if z == '/':
   resultado2 = x / y
   print("o resultado da operação é: ", resultado2)   

elif z == '*':
   resultado3 = x * y
   print("o resultado da operação é: ", resultado3)	


print ("Aqui está a melhor calculadora do mundo!")
