import React, { useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { addExpense, deleteExpense } from './actions';

const ExpenseTracker = () => {
  const [expense, setExpense] = useState('');
  const [amount, setAmount] = useState('');
  const expenses = useSelector(state => state.expenses);
  const dispatch = useDispatch();

  const handleAddExpense = () => {
    if (expense && amount) {
      dispatch(addExpense(expense, amount));
      setExpense('');
      setAmount('');
    }
  };

  return (
    <div className="container mt-5">
      <input
        type="text"
        value={expense}
        onChange={(e) => setExpense(e.target.value)}
        className="form-control"
        placeholder="Expense name"
      />
      <input
        type="number"
        value={amount}
        onChange={(e) => setAmount(e.target.value)}
        className="form-control mt-2"
        placeholder="Amount"
      />
      <button onClick={handleAddExpense} className="btn btn-primary mt-2">Add Expense</button>

      <ul className="list-group mt-3">
        {expenses.map(exp => (
          <li key={exp.id} className="list-group-item d-flex justify-content-between">
            <span>{exp.name} - ${exp.amount}</span>
            <button onClick={() => dispatch(deleteExpense(exp.id))} className="btn btn-danger">Delete</button>
          </li>
        ))}
      </ul>
    </div>
  );
};

export default ExpenseTracker;