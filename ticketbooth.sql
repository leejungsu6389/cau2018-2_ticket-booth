-- phpMyAdmin SQL Dump
-- version 4.8.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- 생성 시간: 18-11-24 11:18
-- 서버 버전: 10.1.36-MariaDB
-- PHP 버전: 5.6.38

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 데이터베이스: `ticketbooth`
--

-- --------------------------------------------------------

--
-- 테이블 구조 `people`
--

CREATE TABLE `people` (
  `id` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `num` int(11) NOT NULL DEFAULT '0',
  `last_t` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 테이블의 덤프 데이터 `people`
--

INSERT INTO `people` (`id`, `num`, `last_t`) VALUES
('88756FFQM52', 9, '2018-11-24 11:17:05');

-- --------------------------------------------------------

--
-- 테이블 구조 `_records`
--

CREATE TABLE `_records` (
  `_od` int(6) NOT NULL,
  `t` datetime NOT NULL,
  `io` varchar(20) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- 테이블의 덤프 데이터 `_records`
--

INSERT INTO `_records` (`_od`, `t`, `io`) VALUES
(1, '0000-00-00 00:00:00', 'IN'),
(2, '2018-11-24 10:55:57', 'IN'),
(3, '2018-11-24 10:57:51', 'OUT'),
(4, '2018-11-24 11:16:48', 'OUT'),
(5, '2018-11-24 11:16:55', 'OUT'),
(6, '2018-11-24 11:17:05', 'IN');

--
-- 덤프된 테이블의 인덱스
--

--
-- 테이블의 인덱스 `people`
--
ALTER TABLE `people`
  ADD PRIMARY KEY (`id`);

--
-- 테이블의 인덱스 `_records`
--
ALTER TABLE `_records`
  ADD PRIMARY KEY (`_od`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
