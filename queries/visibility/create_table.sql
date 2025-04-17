CREATE TABLE IF NOT EXISTS Visibility(
    friend_id INT NOT NULL,
    user_id INT NOT NULL,
    is_visible BOOLEAN DEFAULT FALSE,
    PRIMARY KEY (user_id, friend_id),
    FOREIGN KEY (friend_id) REFERENCES User(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES User(id) ON DELETE CASCADE
);