-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u2
-- http://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Ven 13 Juillet 2018 à 16:24
-- Version du serveur :  5.5.54-0+deb8u1
-- Version de PHP :  5.6.30-0+deb8u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données :  `ruche`
--

-- --------------------------------------------------------

--
-- Structure de la table `mesures`
--

CREATE TABLE IF NOT EXISTS `mesures` (
`id` int(11) NOT NULL,
  `eclairement` float NOT NULL,
  `pression` float NOT NULL,
  `temperature` float NOT NULL,
  `poids` float NOT NULL,
  `humidite` float NOT NULL,
  `tension` float NOT NULL,
  `courant` float NOT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `id_ruche` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Contenu de la table `mesures`
--

INSERT INTO `mesures` (`id`, `eclairement`, `pression`, `temperature`, `poids`, `humidite`, `tension`, `courant`, `date`, `id_ruche`) VALUES
(1, 0, 0, 0, 150.078, 0, 0, 0, '2018-07-13 13:01:05', 1),
(2, 0, 0, 0, 416.244, 0, 0, 0, '2018-07-13 14:20:03', 1);

--
-- Index pour les tables exportées
--

--
-- Index pour la table `mesures`
--
ALTER TABLE `mesures`
 ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `mesures`
--
ALTER TABLE `mesures`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
