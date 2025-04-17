CREATE TABLE IF NOT EXISTS Friendship_Request(
    id INT NOT NULL AUTO_INCREMENT,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    sender_id INT NOT NULL,
    receiver_id INT NOT NULL,
    status ENUM('pending', 'accepted', 'rejected') NOT NULL DEFAULT 'pending',
    PRIMARY KEY (id),
    FOREIGN KEY (sender_id) REFERENCES User(id) ON DELETE CASCADE,
    FOREIGN KEY (receiver_id) REFERENCES User(id) ON DELETE CASCADE
);