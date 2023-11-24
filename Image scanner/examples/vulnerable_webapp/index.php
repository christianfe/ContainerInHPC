<?php
$target = isset($_POST["ip"]) ? $_POST["ip"] : "";
$cmd = isset($_POST["submit"]) && $target != "" ? shell_exec("ping -c 3 " . $target) : "";
?>
<html>

<head>
	<title>My Ping</title>
	<style>
		body {
			background-color: #617867;
		}

		.container {
			width: 1000px;
			margin: auto;
			margin-top: 10px;
			word-wrap: break-word;
			background-color: #b4d9be;
			padding: 1em;
		}

		form,
		h1 {
			text-align: center;
		}
	</style>
</head>

<body>
	<div class="container">
		<h1>Enter the IP to ping</h1>
		<form method="POST">
			<input type="text" name="ip" value="<?php echo $target ?>">
			<input type="submit" name="submit" value="Go!">
		</form>
		<pre><?php echo  $cmd ?></pre>
	</div>
</body>

</html>