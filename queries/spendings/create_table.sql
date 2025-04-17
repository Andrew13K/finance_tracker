CREATE TABLE IF NOT EXISTS Spendings(
    id INT NOT NULL AUTO_INCREMENT,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    category_id INT NOT NULL,
    user_id INT NOT NULL,
    amount DECIMAL(15,2) NOT NULL,
    description TEXT,
    PRIMARY KEY (id),
    FOREIGN KEY (category_id) REFERENCES Category(id) ON DELETE RESTRICT,
    FOREIGN KEY (user_id) REFERENCES User(id) ON DELETE CASCADE,
    CHECK (amount > 0)
);