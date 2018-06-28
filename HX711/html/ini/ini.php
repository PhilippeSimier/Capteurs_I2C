<?php

class ini
{
    var $ini;
    var $filename;

// le constructeur (version php 7)
    function __construct($filename, $commentaire = false) {
        $this->filename = $filename;
        $this->ini = (!$commentaire) ? ' ' : ';'.$commentaire;
    }

// Methode publique pour ajouter les sections
    public function ajouter_array ($array) {
        foreach ($array as $key => $val) {
            if (is_array($val)) {
                $this->sous_tableau($val, $key);
            }
            else if (is_string($key)) {
                $this->ajouter_valeur($key, $val);
            }
        }
    }

// Methode privée pour ajouter une section
    private function sous_tableau ($tab, $groupe = false) {
        if ($groupe) {
            $this->ini .= "\n".'['.$groupe.']';
        }
        foreach ($tab as $key => $val) {
            if (!$this->ajouter_valeur($key, $val))
                return false;
        }
	$this->ini .= "\n";
        return true;
    }

// Méthode privée pour ajouter une valeur dans une section
    private function ajouter_valeur ($key, $val) {
        if (is_array($val)) {
            echo "Erreur : Impossible d'ajouter une valeur";
            return false;
        }
        else if (is_string($val) OR is_double($val) OR is_int($val)) {
            $this->ini .= "\n" . $key . " = " . $val;
        }
        else {
            echo "Erreur : Le type de donnée n'est pas supporté";
            return false;
        }
        return true;
    }

// Méthode public pour écrire le fichier ini
    public function ecrire ($rewrite = false) {
        $c = true;
        if (file_exists($this->filename)) {
            if ($rewrite) {
                @unlink($filename);
            }
            else if (!$rewrite) {
                echo "Erreur fatale : Le fichier ini existe déjà";
                $c = false;
                return false;
            }
        }
        if ($c) {
            $fichier = fopen($this->filename, 'w');
            if (!$fichier) {
                echo "Erreur fatale : Impossible d'ouvrir le fichier";
                return false;
            }
            if (!fwrite($fichier, $this->ini)) {
                echo "Erreur fatale : Impossible d'écrire dans le fichier";
                return false;
            }
            fclose($fichier);
        }
    }
}
?>
