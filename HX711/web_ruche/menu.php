<!----------------------------------------------------------------------------------
    @fichier  menu.php							    		
    @auteur   Philippe SIMIER (Touchard Washington le Mans)
    @date     Juillet 2018
    @version  v1.0 - First release						
    @details  menu /Menu pour toutes les pages du site ruche 
------------------------------------------------------------------------------------>


	<nav class="navbar navbar-expand-md navbar-dark bg-dark fixed-top">
		<a class="navbar-brand" href="index.php">Accueil</a>
		<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarsExampleDefault" aria-controls="navbarsExampleDefault" aria-expanded="false" aria-label="Toggle navigation">
			<span class="navbar-toggler-icon"></span>
		</button>
		<div class="collapse navbar-collapse" id="navbarsExampleDefault">
        <ul class="navbar-nav mr-auto">
			
		  
			    <!-- Dropdown -->
			<li class="nav-item dropdown">
				  <a class="nav-link dropdown-toggle" href="#" id="navbardrop" data-toggle="dropdown">
					Configuration
				  </a>
				  <div class="dropdown-menu">
					<a class="dropdown-item" href="ruche.php">Ruche</a>
					<a class="dropdown-item" href="baseDeDonnees.php">Bases de données</a>
					<a class="dropdown-item" href="balance.php">Balance</a>
				  </div>
			</li>
		  
		  
			<li class="nav-item">
				<a class="nav-link" href="phpmyadmin/">phpMyAdmin</a>
			</li>
          
        </ul>
        
		</div>
    </nav>