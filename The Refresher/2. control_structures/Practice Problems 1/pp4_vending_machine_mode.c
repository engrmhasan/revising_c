/*

A vending machine operator must select a maintenance mode before servicing the unit.
Valid modes are:

| Input | Mode         |
|-------|--------------|
| 1     | Restock      |
| 2     | Diagnostics  |
| 3     | Deep Clean   |
| 4     | Power Off    |

**Your task:**

- Use a `do-while` loop to keep prompting for a mode until a valid one is entered.
- Simulate inputs from a pre-filled `int responses[]` array (include at least two invalid
  values before a valid one, e.g., `{0, 7, 3}`).
- For each invalid input print `"Invalid mode: X. Enter 1-4."`.
- Once a valid mode is accepted, print the active mode name using a **chain of ternary operators**.

*/

