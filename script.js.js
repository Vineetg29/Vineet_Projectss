document.getElementById('contactForm').addEventListener('submit', function(event) {
    event.preventDefault();

    let hasError = false;

    const name = document.getElementById('name').value;
    const email = document.getElementById('email').value;
    const message = document.getElementById('message').value;

    if (name.trim() === '') {
        document.getElementById('nameError').textContent = 'Name is required';
        hasError = true;
    } else {
        document.getElementById('nameError').textContent = '';
    }

    if (email.trim() === '') {
        document.getElementById('emailError').textContent = 'Email is required';
        hasError = true;
    } else if (!validateEmail(email)) {
        document.getElementById('emailError').textContent = 'Email is not valid';
        hasError = true;
    } else {
        document.getElementById('emailError').textContent = '';
    }

    if (message.trim() === '') {
        document.getElementById('messageError').textContent = 'Message is required';
        hasError = true;
    } else {
        document.getElementById('messageError').textContent = '';
    }

    if (!hasError) {
        // Simulate email sending
        setTimeout(() => {
            document.getElementById('successMessage').textContent = 'Thank you for your message!';
            document.getElementById('contactForm').reset();
        }, 1000);
    }
});

function validateEmail(email) {
    const re = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6}$/;
    return re.test(String(email).toLowerCase());
}
