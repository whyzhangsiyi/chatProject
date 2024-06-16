CREATE TABLE `User` (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '用户id',
  `name` varchar(50) NOT NULL COMMENT '用户名',
  `password` varchar(50) NOT NULL COMMENT '用户密码',
  `state` enum('online','offline') DEFAULT 'offline' COMMENT '当前登录状态',
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci ;

CREATE TABLE `FriendId` (
  `userid` int NOT NULL COMMENT '用户id',
  `friend` int NOT NULL COMMENT '好友id'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci ;


CREATE TABLE `AllGroup` (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '组id',
  `groupname` varchar(50) NOT NULL COMMENT '组名称',
  `groupdesc` varchar(200) DEFAULT '' COMMENT '组功能描述',
  PRIMARY KEY (`id`),
  UNIQUE KEY `groupname` (`groupname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci ;


CREATE TABLE `GroupUser` (
  `groupid` int NOT NULL COMMENT '组id',
  `userid` int NOT NULL COMMENT '组员id',
  `grouprole` enum('creator','normal') DEFAULT 'normal' COMMENT '组内角色'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci ;

CREATE TABLE `OfflineMessage` (
  `userid` int NOT NULL COMMENT '用户id',
  `message` varchar(500) NOT NULL COMMENT '离线消息（存储Json字符串）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci ;
