This C code simulates a lottery system, similar to Brazil's "Mega-Sena," allowing a user to place bets. The program supports manual bets, randomly generated bets ("surpresinha"), and allows multiple draws using the same bets ("teimosinhas"). Here’s a brief breakdown:

Input Functions:
QD, QM, QS, QT: Collect the number of dozens to bet, the number of manual bets, the number of random bets, and the number of draws with the same bet.

Bet Placement:
AM: Fills in manual bets, ensuring no repeated numbers.
AS: Generates random bets without repeating numbers.

Lottery Draw:
megaS: Randomly generates winning numbers for each draw.

Checking Results:
acertos: Compares the user’s bets against the drawn numbers to count how many numbers matched.
premios: Calculates potential winnings based on matches.

Display:
imprimir: Displays the results of the bets, the drawn numbers, the total cost, and potential winnings.

Main Function:
Orchestrates the entire process, from taking user inputs to displaying results and freeing memory.
The program calculates the total cost of the bets, checks for winnings, and displays results after each draw. It also handles input validation and avoids duplicate numbers in bets.
