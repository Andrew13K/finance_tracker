CREATE TABLE IF NOT EXISTS Friends(
    friend_id INT NOT NULL,
    user_id INT NOT NULL,
    PRIMARY KEY (user_id, friend_id),
    FOREIGN KEY (friend_id) REFERENCES User(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES User(id) ON DELETE CASCADE
);