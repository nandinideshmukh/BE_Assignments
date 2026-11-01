
import hashlib
import json
import os
from datetime import datetime


FILE_NAME = "medical_blockchain.json"


class Block:
    def __init__(self, index, timestamp, data, previous_hash):
        self.index = index
        self.timestamp = timestamp
        self.data = data
        self.previous_hash = previous_hash
        self.hash = self.calculate_hash()

    def calculate_hash(self):
        block_data = {
            "index": self.index,
            "timestamp": self.timestamp,
            "data": self.data,
            "previous_hash": self.previous_hash
        }

        encoded_data = json.dumps(
            block_data, sort_keys=True
        ).encode()

        return hashlib.sha256(encoded_data).hexdigest()

    def to_dict(self):
        return {
            "index": self.index,
            "timestamp": self.timestamp,
            "data": self.data,
            "previous_hash": self.previous_hash,
            "hash": self.hash
        }


class MedicalBlockchain:
    def __init__(self):
        self.chain = []
        self.load_chain()

        if not self.chain:
            genesis = Block(
                0,
                datetime.now().isoformat(),
                {"message": "Genesis Block"},
                "0"
            )
            self.chain.append(genesis)
            self.save_chain()

    def save_chain(self):
        with open(FILE_NAME, "w") as file:
            json.dump(
                [block.to_dict() for block in self.chain],
                file,
                indent=4
            )

    def load_chain(self):
        if not os.path.exists(FILE_NAME):
            return

        try:
            with open(FILE_NAME, "r") as file:
                records = json.load(file)

            for item in records:
                block = Block(
                    item["index"],
                    item["timestamp"],
                    item["data"],
                    item["previous_hash"]
                )
                # Preserve the stored hash for verification.
                block.hash = item["hash"]
                self.chain.append(block)

        except (OSError, ValueError, KeyError, TypeError) as error:
            print("Could not load blockchain:", error)
            self.chain = []

    def add_record(self):
        patient_id = input("Enter patient ID: ").strip()
        name = input("Enter patient name: ").strip()
        diagnosis = input("Enter diagnosis: ").strip()
        prescription = input("Enter prescription: ").strip()

        if not all([patient_id, name, diagnosis, prescription]):
            print("All fields are required.")
            return

        # Educational demo only: do not enter real medical data.
        record = {
            "patient_id": patient_id,
            "name": name,
            "diagnosis": diagnosis,
            "prescription": prescription
        }

        previous_block = self.chain[-1]

        new_block = Block(
            len(self.chain),
            datetime.now().isoformat(),
            record,
            previous_block.hash
        )

        self.chain.append(new_block)
        self.save_chain()

        print("\nMedical record added successfully!")
        print("Block hash:", new_block.hash)

    def view_records(self):
        print("\n===== MEDICAL BLOCKCHAIN =====")

        for block in self.chain:
            print(f"\nBlock number: {block.index}")
            print("Timestamp:", block.timestamp)
            print("Record:", json.dumps(block.data, indent=2))
            print("Previous hash:", block.previous_hash)
            print("Block hash:", block.hash)

    def verify_chain(self):
        for i, block in enumerate(self.chain):
            if block.hash != block.calculate_hash():
                print(f"FAILED: Block {i} has been modified.")
                return

            if i == 0:
                if block.previous_hash != "0":
                    print("FAILED: Invalid genesis block.")
                    return
            else:
                previous_block = self.chain[i - 1]

                if block.previous_hash != previous_block.hash:
                    print(f"FAILED: Block {i} link is invalid.")
                    return

                if block.index != previous_block.index + 1:
                    print(f"FAILED: Block {i} index is invalid.")
                    return

        print("SUCCESS: Blockchain integrity verified!")

    def menu(self):
        while True:
            print("\n===== MEDICAL RECORD SYSTEM =====")
            print("1. Add medical record")
            print("2. View all records")
            print("3. Verify blockchain")
            print("4. Exit")

            choice = input("Enter your choice: ").strip()

            if choice == "1":
                self.add_record()
            elif choice == "2":
                self.view_records()
            elif choice == "3":
                self.verify_chain()
            elif choice == "4":
                print("Exiting system.")
                break
            else:
                print("Invalid choice. Try again.")


if __name__ == "__main__":
    app = MedicalBlockchain()
    app.menu()
