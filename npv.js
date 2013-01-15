$(document).ready(
  function() {
    $('#edit-verein').blur(
      function() {
    	vlic = $('#edit-verein').val().substring(0,7);
    	slic = $('#edit-verein').val().substring(8,11);
    	verein = $('#edit-verein').val().substring(14);
    	$('#edit-vereinslizenz').val(vlic);
        $('#edit-lizenz').val(slic);
        $('#edit-verein').val(verein);
      }
    );
  }
);