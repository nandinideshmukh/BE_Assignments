// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract BankAccount {

    // Stores the balance of each user's account
    mapping(address => uint256) private balances;

    // Deposit Ether into the bank account
    function deposit() public payable {
        require(msg.value > 0, "Deposit amount must be greater than zero");

        balances[msg.sender] += msg.value;
    }

    // Withdraw Ether from the bank account
    function withdraw(uint256 amount) public {
        require(amount > 0, "Withdrawal amount must be greater than zero");
        require(balances[msg.sender] >= amount, "Insufficient balance");

        // Update balance before transferring Ether
        balances[msg.sender] -= amount;
        (bool success,) = payable (msg.sender).call{value:amount}("");
        require(success, "Transfer failed");
    }

    // Display the balance of the caller
    function getBalance() public view returns (uint256) {
        return balances[msg.sender];
    }
}